# CESE2018_TestingSoftROliva - updated 05.2022

TP3 of Embedded Software Testing - Revision 2022 - Added documentation in
english at the /doc directory, where the procedure and test file is listed.
 
This repository contains files and procedure used for testing one of the sections the /stats module in /modules/stats of the PWRC2 application running on CL2 boards, now in its version 10a. This specific section computes vector averages of wind direction based on METEO board wind-vane measurements, transmitted via RS485 to the CL2 main CPU boards. These modules are originally compiled in CVAVR Codevision IDE for AVR. Most higher level modules can be tested using Ceedling running on Linux in a separate virtual machine because they are not dependant on hardware details. 


# Original: 
(Trabajos TP3 de R.Oliva - Materia Testing de Software 10-2018
Ensayo de stats_sp (Estadisticas  de direccion de viento y 
de densidad de aire - que deben correr en Placa prototipo Final)
