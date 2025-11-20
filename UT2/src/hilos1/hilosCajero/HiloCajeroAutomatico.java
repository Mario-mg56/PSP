package hilos1.hilosCajero;

public class HiloCajeroAutomatico {
    public static void main(String[] args) throws InterruptedException{
    	CuentaBancaria cuenta = new CuentaBancaria(1000);
    	HiloIngresarDinero padre = new HiloIngresarDinero(cuenta, "padre", 200);
    	HiloSacarDinero madre = new HiloSacarDinero(cuenta, "madre", 800);
    	HiloIngresarDinero hijo1 = new HiloIngresarDinero(cuenta, "hijo1", 300);
    	HiloSacarDinero hijo2 = new HiloSacarDinero(cuenta, "hijo2", 800);
    	HiloSacarDinero abuelo = new HiloSacarDinero(cuenta, "abuelo", 600);
    	padre.start();
    	padre.join();
    	madre.start();
    	madre.join();
    	hijo1.start();
    	hijo1.join();
    	hijo2.start();
    	hijo2.join();
    	abuelo.start();
    	abuelo.join();
    }
}