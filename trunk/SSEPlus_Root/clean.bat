::
:: Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
:: This software is subject to the Apache v2.0 License.
::


del /s *.ncb
del /s *.opt
del /s *.user
del /s /AH *.suo

rmdir /s /q build
rmdir /s /q Documentation\publish\html
rmdir /s /q Documentation\CSVToDox\Debug

pause

