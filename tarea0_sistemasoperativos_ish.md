
Tarea 1- Sistemas operativos - Ian Schmidt


Para esta primera tarea se instaló ubuntu y las herramientas necesarias para poder ejecutar xv6 correctamente


En primer lugar se busco en internet ejemplos de como lo hacian otras personas y cuales eran los pasos necesarios para poder lograr una ejecución correcta, para realizar una introducción y poder completar las siguientes tareas a traves de la plataforma.
Se realizo la instalación con los siguientes comandos

wsl --install

sudo apt-get update

sudo apt-get install build-essential qemu-system-x86 git

git clone https://github.com/mit-pdos/xv6-public.git

cd xv6-public

make

make qemu

Luego de eso se generaron las pruebas para ver si funcionada correctamente, siendo ese el caso. Al comienzo fue dificil ya que no tenia mucha informacion, pero luego de investigar se logro correctamente la instalación. 

