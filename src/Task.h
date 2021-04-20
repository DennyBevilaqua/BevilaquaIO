#ifndef Task_h
#define Task_h

#include "Arduino.h"

class TaskClass
{

public:
    typedef void (*CallbackType)(void);
    int interval;
    unsigned long nextRun;
    CallbackType callback;

    void set (CallbackType call, int intervalA)
    {
        callback = call;
        interval = intervalA;
        nextRun = 0;
    }

    void execute()
    {
        callback();
    }
};

class TaskMan
{
private:
    short numTasks;
    TaskClass *tasks[10];

public:
    TaskMan()
    {
        numTasks = 0;
        *tasks = new TaskClass[10];
    }

    void add(TaskClass::CallbackType call, int intervalA)
    {
        tasks[numTasks]->set(call, intervalA);
        numTasks++;
    }

    void loop()
    {
        for (short i = 0; i < numTasks; i++)
        {
            TaskClass *c = getTask(i);

            if (c->nextRun <= millis())
            {
                c->nextRun += c->interval;
                c->execute();
            }
        }
    }

    TaskClass *getTask(int i)
    {
        return tasks[i];
    }
};

TaskMan Tasks;
#endif