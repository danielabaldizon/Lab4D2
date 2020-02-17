#DANIELA BALDIZON
#17005
#LAB4 DIGITAL 2
#REF1: https://pythonprogramming.net/converting-python-scripts-exe-executables/?completed=/threading-tutorial-python/

from tkinter import *
import serial
import sys
import time

#CONEXION SERIAL
try:
    ser = serial.Serial(port='COM9', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
                        bytesize=serial.EIGHTBITS, timeout=0)
    ser.setDTR(False)
    time.sleep(1)
    ser.flushInput()
    ser.setDTR(True)
    print("CONEXIÓN EXITOSA")

except:
    print("NO SE PUDO REALIZAR LA CONEXIÓN")

control = 0

#FUNCION PARA SALIR
def client_exit():
    exit()

#FUNCION PARA ENVIAR Y BORRAR EL TEXTO
def client_enviar():
    escritura = entry.get() #AGARRAR EL DATO ESCRITO
    enviado = (int(escritura)).to_bytes(1, byteorder = 'big') #PASAR A CHAR EL VALOR
    ser.write(enviado)  #ENVIAR SERIALMENTE
    entry.delete(0, END) #BORRAR TODO LO QUE ESTA ESCRITO EN EL CAMPO 

    

root = Tk()
root.title("SPI")
#TAMAÑO DE LA VENTANA
root.geometry("400x300")

# creating a button instance
quitButton = Button(root, text="SALIR",command=client_exit)

# placing the button on my window
quitButton.place(x=0, y=0)

#ENTRADA DE VALOR
entry = Entry(root)
entry.place(x=70,y=70)

#BOTON PARA ENVIAR
enviar = Button(root, text="Enviar",command=client_enviar)

#PONER EL BOTON
enviar.place(x=200, y=70)


#PONER LABEL
w = Label(root, text="DANIELA BALDIZON")
w.pack()

vol1=Label(root, text="El valor del potenciometro 1 es")
vol1.place(x=100,y=150)

vol1=Label(root, text="El valor del potenciometro 2 es")
vol1.place(x=100,y=210)

voltajem = Label(root, font=("Times new roman",18))
voltajem.place(x=175, y=175)

voltajem2 = Label(root, font=("Times new roman",18))
voltajem2.place(x=175, y=230)

voltajev=0
plex = 1
flag = 0

while 1:
    ser.flushInput()
    ser.flushOutput()
    recibido1 = ser.readline()
    try:
        numero = ord(recibido1)
       # print(numero)
        voltajev = float(numero/51.0)
        voltajev=round(voltajev,2)
        rest = abs(voltajev-control)
      #  if (rest>2):
       #     voltajev = 0;
        if (plex == 1):
            voltajem.config (text = voltajev)
            print(numero)
            plex = 2
        elif (plex == 2):
            voltajem2.config (text = voltajev)
            print(numero)
            plex = 1
        control=voltajev
        print(plex)
    except:
        x=0
    root.update()

root.mainloop()
