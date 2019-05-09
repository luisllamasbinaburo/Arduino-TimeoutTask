/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "TimeoutTask.h"

const size_t dataLength = 10;
int data[dataLength];
const int bytesLengths = dataLength * sizeof data[0];

void setup()
{
  TimeoutTask::Run(50000,
	[]() { return Serial.available() >= dataLength; },
	[]() { Serial.readBytes(reinterpret_cast<byte*>(data), dataLength * sizeof data[0]); },
	[]() {});
}

void loop()
{
}
