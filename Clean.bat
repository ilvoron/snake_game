@echo off
@echo Cleaning...
@if exist "build" rmdir /Q /S "build" || @echo Cleaning... Error! & @echo Press any key to exit... & @pause > nul & exit \b
@echo Cleaning... Done!
@echo Press any key to exit...
@pause > nul