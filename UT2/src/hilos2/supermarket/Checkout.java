package hilos2.supermarket;

public class Checkout {
	private int id;
	public boolean busy;
	public Checkout(int id) {
		this.id = id;
		this.busy = false;
	}
	
	public synchronized void cobrar(Costumer costumer) throws InterruptedException {
		System.out.println("Caja " + id + " atendiendo a " + costumer);
		Thread.sleep(3000);
		System.out.println("Caja " + id + " ha atendido a " + costumer);
		busy = false;
	}
}
