class Task
{
    private:
        typedef void (*CallbackType)(void);
        short numTasks;
        int time;
        unsigned long lastRun;
        CallbackType callback;
        Task* tasks[];
        void execute();
    
    public:
        Task(CallbackType call = 0, int timeA = 0);
        void add(CallbackType call, int timeA);
        void loop();
        Task* getTask(int i);
};
