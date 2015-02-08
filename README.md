Insert this entry into the boards.txt file in the arduino hardware folder for support for FTWatch

##############################################################

mega.name=FR Watch

mega.upload.protocol=arduino
mega.upload.maximum_size=126976
mega.upload.speed=57600

mega.bootloader.low_fuses=0xE2
mega.bootloader.high_fuses=0x5A
mega.bootloader.extended_fuses=0xFD
mega.bootloader.path=atmega
mega.bootloader.file=ATmegaBOOT_168_atmega1280.hex
mega.bootloader.unlock_bits=0x3F
mega.bootloader.lock_bits=0x0F

mega.build.mcu=atmega1280
mega.build.f_cpu=8000000L
mega.build.core=arduino
mega.build.variant=mega


