package hilos2.supermarket;

public class Costumer extends Thread{
	int id;
	public Costumer(int id) {this.id = id;}
	
	@Override
	public void run() {
		System.out.println(id + " entra en la cola de espera");
		try {
			Checkout checkout  = Supermarket.getInstance().assignCheckout();
			checkout.cobrar(this);
		}
		catch (InterruptedException ex) {ex.printStackTrace();}
		System.out.println(id + " sale del supermercado");
	}
	
	@Override
	public String toString() {return id + "";} 
}
