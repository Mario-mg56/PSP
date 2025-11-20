package hilos2.supermarket;

import java.util.ArrayList;

public class Supermarket {
	static Supermarket instance;
	ArrayList<Checkout> checkouts;
	public ArrayList<Costumer> costumers;
	
	private Supermarket(int numCheckouts, int numCostumers) {
		this.checkouts = new ArrayList<>();
		this.costumers = new ArrayList<>();
		for (int i = 1; i<=numCheckouts; i++) checkouts.add(new Checkout(i));
		for (int i = 1; i<=numCostumers; i++) costumers.add(new Costumer(i));
	}
	
	public static Supermarket setInstance(int numCheckouts, int numCostumers) {
		if (numCheckouts <= 0 || numCostumers <= 0) return null;
		else instance = new Supermarket(numCheckouts, numCostumers);
		return instance;
	}
	public static Supermarket getInstance() {return instance;}
	
	public synchronized Checkout assignCheckout() {
		while(true) {
			for (Checkout c : checkouts) if (!c.busy) {
				c.busy = true;
				return c;
			}
		}
	}
	
	public void start() throws InterruptedException {
		for (Costumer c : costumers) c.start();
		for (Costumer c : costumers) c.join();
		System.out.println("El supermercado está cerrado");
	}
	
	public static void main(String args[]) throws InterruptedException {
		Supermarket.setInstance(3, 20).start();
	}
}