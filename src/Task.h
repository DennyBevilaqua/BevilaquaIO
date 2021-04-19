#include "Arduino.h"

class Task
{
private:
    typedef void (*CallbackType)(void);
    short numTasks;
    int time;
    unsigned long lastRun;
    CallbackType callback;
    Task *tasks[];
    void execute()
    {
        callback();
    }

public:
    Task(CallbackType call = 0, int timeA = 0)
    {
        callback = call;
        time = timeA;
        lastRun = 0;
        numTasks = 0;
        *tasks = new Task[0];
    }

    void add(CallbackType call, int timeA)
    {
        Task *task = new Task(call, timeA);
        auto oTasks = *tasks;
        *tasks = new Task[numTasks + 1];

        for (short i = 0; i < numTasks; i++)
        {
            Task *t = &oTasks[i];
            tasks[i] = t;
        }

        tasks[numTasks] = task;
        numTasks++;

        task->lastRun = 0;
        tasks[numTasks] = task;
    }

    void loop()
    {
        for (short i = 0; i < numTasks; i++)
        {
            Task *c = getTask(i);
            unsigned long cTime = millis();
            unsigned long nTime = c->lastRun + c->time;

            if (c->lastRun == 0)
                nTime = 0;

            if (cTime >= nTime)
            {
                c->lastRun = cTime;
                c->execute();
            }
        }
    }

    Task *getTask(int i)
    {
        return tasks[i];
    }
};
