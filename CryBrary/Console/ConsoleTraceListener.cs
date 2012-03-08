﻿using System.Diagnostics;

namespace CryEngine
{
    partial class Debug
    {
        class CryTraceListener : TraceListener
        {
            public override void Write(string message)
            {
                WriteLine(message);
            }

            public override void WriteLine(string message)
            {
                Debug.Log(message);
            }

            public override void TraceEvent(TraceEventCache eventCache, string source, TraceEventType eventType, int id, string message)
            {
                switch (eventType)
                {
                    default:
                        Debug.Log(message);
                        break;
                }
            }
        }
    }
}