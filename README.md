# TestAntivirus

## �������
�� ����� �� ����� ���������� ����� ����������� ����� � �� virustotal ��� �� ��������� �� ���� ���������, �� ��������� �������������� � ����������� � ������ �������� ���� ������������ ����������� �������.

� ��� ���� ���� ������ ["Virus.bin"](https://cloud.mail.ru/public/8gKU/ELCWprct4) � ���� � ����� �������� ["main.cvd"](https://cloud.mail.ru/public/B43h/y6VS2TTpU)
 (������ � ����� "���� ��������") ����������� open-source ����������. �� ��� ��������, ���� ���� �������� ����� �������� ������ cvd.

�������:

1. C�������������� ��������� ���� �������� � ��������� ��� ��� ���������� ������ �������. (���������: ����, ����� ��������� �����������, ������ ������� �������).

2. �������� ��������� ������ _"virus.bin"_ � ����������������� ���� ��������� ��������.

3. �������� ��������� ������ �� C/C++ � ����������� ����������� �����������, ������� ����� ��������� �� ���� ����, ������ ��������� �� ���� �������� � �������� ��������� �������/�� �������.

�� ���������� ������� ������ 48 �����.
���������� ���������� �������, � ��� �� ������������� ������� � ������� ���������� � ���� ����������� github.

## ������� ������������ ������

### ����������� ������� ���� ��������

* �� ��������� � ������� ���������� �������� ���������� �� _".rar"_, _".zip"_, _".7z"_ � ������� ����������� WinRar, �.�. �� ����� ��������� ������ � ������ ������������. �� �� ����.
* ������ � ��������� ���� _"main.cvd"_
* ������ � ���������� **ClamAV-VDB**
* ������ � ��������� ["ClamWin"](http://ru.clamwin.com/). � ������� ��� ������� **sigtool.exe** � ������� ***unpack*** ���������� _"main.cvd"_ � ["main.mdb"](https://cloud.mail.ru/public/GN3N/RimYKCNGh).
* ������ � ��������� � ��������� ������ ��������:

	***������:MD5:���������***

	***������:MD5:���������***

	***...***

* �������� ������, MD5 _"Virus.bin"_ � � ������� ��������� ������� � _"main.mdb"_.

### �������� ������

* ����� ���� � ������������ �����, ���������� ��� ������� � MD5.
* ���������� ���������� �������� � "main.mdb" � ��������� �� ������� � MD5.
* �������� ������������ ������� ����������� ��������.
* ���� ����� ���������� �������.
* ����������� ������������ � �����������.

### ����������

* MSVC 2013
* C++/STL
* WinAPI/WinCrypto

### ��������� ����������

* CPU: 1 GHz
* RAM: 6 Mb
* HDD: 250 kb

### ���������

Windows 7/8 (x86/x64).

### �������� ����������

������� �� ������ ������������ �����: Win32Project1.exe. ���� ���� �������� �������� ***"main.mdb"*** ������ ���� � ����� �������� � �����������. 

### ����������� ������������� ����������

�������� ***"Help.docx"***.

### �������� �������

* ***App*** �������� �� GUI: ����� �����/������ ��������/����������� � ��������� ���� ��������� ��������/���������� ��������/�������� ���������.
* ***FileScan*** ��������� �������� ���������� ������������� �����.
* ***Thread*** ������������� ������� WinAPI ��� ������ � �������. ���������� ���, �.�. ����� thread � �++11 ��� ��������� �� ������ + � �������� �� WinAPI ����� ������������ �������� ������������, ��� �������� ����� ��� ���������� ��������� ��.
* ***AutoEvent*** ������������� ������� WinAPI ��� ������ � ��������� � �������������� �������. ������������ ��� ����������� ���������� ������ �������� ��� ������ ��������.
* ***CriticalSection*** ������������� ������� WinAPI ��� ������ � ����������� �������. ������������ � ������ Thread ��� ��������� � ����������� ������� ������: ��������/�� ��������.
* ***DialogFile*** ������������� ������� WinAPI ������ ����� � ������� ������������ ����������� ���� Windows.
* ***TextBox, Button*** ������������ ��� ���������� ������� ���������.
* ***WinApiException*** ��� ��������� ������ ������� WinAPI.
* ***HandleThread � HandleEvent*** ������� ��� �������� ����������� ������ � �������.
* ***HandleWinCryptoProvider � HandleWinCryptoHash*** ������� ��� �������� ����������� ������������������ ����������, ������������ ��� ���������� MD5.
* ***HashMD5*** ��������� MD5 ������.
* ***FileHash*** ��������� ��� �����.
* ***ParamToScan*** ���������, ��� �������� ���������� ������ FileScan.

### ��������� �������

�������� ���� ***"ClassDiagram.png"***.

### ������������ �������

����������� ����������, ���� ����� ���� ��������� ����������. ��������, �������� ����� ��� ������������: ���� ������� ��� �������. 

### ���������� �������

1. ��-�� ���������� � STL �������� ���������� ���� � �����������. **� ������ ���� ������ ���� �� ����� ��, � ��������� .dll**. 
2. ��� ����� ��� �������� ������������ ������� _CreateProcess_ � ������������� _ClamAv_, �� ����� �� ������� �� ������������������ ���� ������.

### ������� ����������� �����

20 ����� �� ��������������, ���������� � �������.
