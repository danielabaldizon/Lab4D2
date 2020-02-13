#DANIELA BALDIZON
#17005
#LAB4 DIGITAL 2
#REF1: https://pythonprogramming.net/converting-python-scripts-exe-executables/?completed=/threading-tutorial-python/

from tkinter import *
import serial
import sys

#CONEXION SERIAL
try:
    ser = serial.Serial(port='COM9', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
                        bytesize=serial.EIGHTBITS, timeout=0)
    ser.setDTR(False)
    ser.flushInput()
    ser.setDTR(True)
    print("CONEXIÓN EXITOSA")

except:
    print("NO SE PUDO REALIZAR LA CONEXIÓN")

#FUNCION PARA SALIR
def client_exit():
    exit()

#FUNCION PARA ENVIAR Y BORRAR EL TEXTO
def client_enviar():
    escritura = entry.get() #AGARRAR EL DATO ESCRITO
    enviado = chr(int(escritura)) #PASAR A CHAR EL VALOR
    ser.write(bytes(enviado.encode())) #ENVIAR SERIALMENTE
    print(enviado)
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




root.mainloop()
