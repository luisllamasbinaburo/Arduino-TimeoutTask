/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "TimeoutTask.h"

void TimeoutTask::Run() const
{
	Run(_timeout, _conditionFunc, _okCallback, _timeoutCallback);
}

void TimeoutTask::Run(unsigned long timeout, ConditionFunc cond, CallbackAction okCallback, CallbackAction timeoutCallback)
{
	unsigned long starttime;
	bool timeExceed = true;
	starttime = micros();

	while (timeExceed == true && (micros() - starttime) < timeout)
	{
		if (cond()) timeExceed = false;
	}
	if (timeExceed) timeoutCallback();
	else okCallback();
}