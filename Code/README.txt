Created by : Filip Juza

To launch program correctly, provide absolute path for sqlite database
in Sources/Controller/databasecontroller.cpp (in constructor).
Otherwise, program will not run correctly.

Program is a tool for doctors who run their own businesses.
User can :
- add a patient to existing patients list
- find information about existing patient
- add a visit for an existing patient
- edit data of a visit / patient and store it
- delete a visit
- delete a patient
