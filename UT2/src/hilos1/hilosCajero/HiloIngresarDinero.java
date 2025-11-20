package hilos1.hilosCajero;

class HiloIngresarDinero extends Thread {
    private CuentaBancaria cuenta;
    private String nombre;
    private int cantidad;

    public HiloIngresarDinero(CuentaBancaria micuenta, String nombre, int cantidad){
    	this.cuenta = micuenta;
    	this.nombre = nombre;
    	this.cantidad = cantidad;
    	
    }

    @Override
    public void run() {
    	cuenta.ingresarDinero(nombre, cantidad);
    }
}