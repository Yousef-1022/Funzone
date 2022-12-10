class Engine
{

private:

    bool isRunning = false;

public:

    void start() { isRunning = true; }
    void stop() { isRunning = false; }
    bool isEngineRunning() { return isRunning; }

};

