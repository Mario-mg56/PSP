package hilos1.hilosCajero;

public class HiloSacarDinero extends Thread {
    private CuentaBancaria cuenta;
    private String nombre;
    private int cantidad;

    public HiloSacarDinero(CuentaBancaria micuenta, String nombre, int cantidad){
    	this.cuenta = micuenta;
    	this.nombre = nombre;
    	this.cantidad = cantidad;
    }
    
    @Override
    public void run() {
    	cuenta.sacarDinero(nombre, cantidad);
    }
}