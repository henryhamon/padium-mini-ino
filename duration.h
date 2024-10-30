#ifndef DURATION_H
#define DURATION_H

// Duration
typedef struct
{
    unsigned long time_start;
    unsigned long durationMs;
} Timer;

// Duration Functions
//
Timer initTimer(unsigned long durationMS)
{
    return {millis(), durationMS};
}

boolean timeNotExpired(Timer time)
{
    return millis() - time.time_start < time.durationMs;
}

#endif
