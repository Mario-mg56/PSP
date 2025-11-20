package hilos1.hilosCajero;

class CuentaBancaria {
	int saldo;
	
	public CuentaBancaria(int saldo) {
		this.saldo = saldo;
	}
	
    public void sacarDinero (String nombre, int importe){
        try {
        	System.out.println(nombre + " está intentando sacar dinero...");
        	Thread.sleep(1000);
        	int saldo = this.saldo-importe;
        	if (saldo<0) System.out.println("Operación fallida: No hay suficiente dinero");
        	else {
        		this.saldo = saldo;
        		System.out.println("Exito: saldo actual " + this.saldo);
        	}
        }
        catch (InterruptedException e) {e.printStackTrace();}
    }
    
    public void ingresarDinero (String nombre, int importe){
        try {
        	System.out.println(nombre + " está intentando meter dinero...");
        	Thread.sleep(1000);
        	saldo += importe;
        	System.out.println("Exito: saldo actual " + saldo);
        }
        catch (InterruptedException e) {e.printStackTrace();}
    }
}