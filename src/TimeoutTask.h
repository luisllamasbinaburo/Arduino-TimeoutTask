/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#ifndef _TimeoutTaskLib_h
#define _TimeoutTaskLib_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class TimeoutTask
{
	typedef bool(*ConditionFunc)();
	typedef void(*CallbackAction)();

public:
	TimeoutTask(unsigned long timeout, bool(*conditionFunc)(), void(*okCallback)(), void(*timeoutCallback)())
		: _timeout(timeout), _conditionFunc(conditionFunc), _okCallback(okCallback), _timeoutCallback(timeoutCallback)
	{
	}

	void Run() const;

	static void Run(unsigned long timeout,
		ConditionFunc conditionFunc,
		CallbackAction okCallback,
		CallbackAction timeoutCallback);

private:
	unsigned long _timeout;
	ConditionFunc _conditionFunc;
	CallbackAction _okCallback;
	CallbackAction _timeoutCallback;

};
#endif
