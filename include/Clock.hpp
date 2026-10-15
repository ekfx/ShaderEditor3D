#pragma once

#include <chrono>

class Clock
{
  private:
    bool firstTime = true;
    std::chrono::duration<double> DELTA;
    std::chrono::steady_clock::time_point TICK;
    std::chrono::steady_clock::time_point A;
    std::chrono::steady_clock::time_point B;

  public:
    void Run() noexcept
    {
        if (firstTime)
        {
            TICK = std::chrono::steady_clock::now();
            DELTA = std::chrono::duration<double>(0);
            B = std::chrono::steady_clock::time_point();

            A = std::chrono::steady_clock::now();
            firstTime = false;
        }
        else
        {
            B = std::chrono::steady_clock::now();
            DELTA = B - A;
            A = B;
        }
    }

    double Frametime() noexcept { return DELTA.count(); }

    float FPS() noexcept { return (1.0 / DELTA.count()); }

    bool Tick(const float &s) noexcept
    {
        if ((B - TICK).count() >= s)
        {
            TICK = std::chrono::steady_clock::now();
            return true;
        }
        else
        {
            return false;
        }
    } // one timer per run
};
