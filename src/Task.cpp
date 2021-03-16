#include "Task.h"
#include "Arduino.h"

Task::Task(CallbackType call, int timeA)
{
    callback = call;
    time = timeA;
    lastRun = 0;
    numTasks = 0;
    *tasks = new Task[0];
}

Task* Task::getTask(int i)
{
    return tasks[i];
}

void Task::add(CallbackType call, int timeA)
{
    Task* task = new Task(call, timeA);
    auto oTasks = *tasks;
    *tasks = new Task[numTasks +1];

    for (short i = 0; i < numTasks; i++)
    {
        Task* t = &oTasks[i];    
        tasks[i] = t;
    }
    
    tasks[numTasks] = task;
    numTasks++;

    task->lastRun = 0;
    tasks[numTasks] = task;
}

void Task::seed()
{
    for (short i = 0; i < numTasks; i++)
    {
        Task* c = getTask(i);
        unsigned long cTime = millis();        
        unsigned long nTime = c->lastRun + c->time;

        if(c->lastRun == 0)
            nTime = 0;

        if(cTime >= nTime)
        {
            c->lastRun = cTime;
            c->execute();
        }
    }
}

void Task::execute()
{
    callback();
}