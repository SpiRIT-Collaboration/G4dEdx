Calculate dE/dx lines using GEANT4
=
Originally arranged by Rensheng from a GEANT4 example

Configuration
-
- Beam is fixed to z direction.
- TPC volume: (1000, 530, 12) mm
- B-field: (0, 0.5, 0) T
- Max. step length in TPC: 0.5 mm

How to change settings
-
- TPC volume: [bin/Linux-g++/Config/Geo_Size.config](https://github.com/SpiRIT-Collaboration/G4dEdx/blob/master/bin/Linux-g%2B%2B/Config/Geo_Size.config)
- Batch mode: [Line 4 of bin/Linux-g++/Config/Initial.config](https://github.com/SpiRIT-Collaboration/G4dEdx/blob/master/bin/Linux-g%2B%2B/Config/Initial.config#L4)
- Number of events: [Line 5 of bin/Linux-g++/Config/Initial.config](https://github.com/SpiRIT-Collaboration/G4dEdx/blob/master/bin/Linux-g%2B%2B/Config/Initial.config#L5)

How to run
-
1. Load GEANT4 environmental variables.
2. Type `source env.sh` to set G4WORKDIR to the current directory.
3. Type `make` to compile.
4. Open [bin/Linux-g++/ControlRun_MultiProcess.sh](https://github.com/SpiRIT-Collaboration/G4dEdx/blob/master/bin/Linux-g%2B%2B/ControlRun_MultiProcess.sh) file with any text editor.
5. Change Lines 7-10. Note that lines 8-9 are only active when `ParticleName` is `2H`, `3H`, `3He` or `4He`.
6. If the particle you set is heavior than proton, make sure to set correct number of `ParticleA` and `ParticleZ`.
7. Change the number in line 17 depending on your CPU cores.
8. Save an exit the text editor.
9. Run [bin/Linux-g++/ControlRun_MultiProcess.sh](https://github.com/SpiRIT-Collaboration/G4dEdx/blob/master/bin/Linux-g%2B%2B/ControlRun_MultiProcess.sh).
