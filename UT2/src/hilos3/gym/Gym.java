package hilos3.gym;

import java.util.ArrayList;

public class Gym {
    static Gym instance;
    int capacity, currentCapacity;
    ArrayList<Costumer> costumers;
    public Gym (int numCostumers, int capacity) {
        this.currentCapacity = 0;
        this.capacity = capacity;
        this.costumers = new ArrayList<>();
        for (int i = 1; i <= numCostumers; i++) costumers.add(new Costumer(i));
    }

    public static Gym setInstance(int numCostumers, int capacity) {
        if (numCostumers <= 0 || capacity <= 0) return null;
        else instance = new Gym(numCostumers, capacity);
        return instance;
    }
    public static Gym getInstance() {return instance;}

    public void access(Costumer costumer) throws InterruptedException {
        synchronized (this) {
            while (currentCapacity >= capacity) wait();
            currentCapacity++;
        }
        costumer.train();
        synchronized (this) {
            currentCapacity--;
            notifyAll();
        }
    }

    public void start() throws InterruptedException {
        for (Costumer costumer : costumers) costumer.start();
        for (Costumer costumer : costumers) costumer.join();
        System.out.println("El gimnasio está cerrado");
    }

    public static void main(String[] args) throws InterruptedException {
        Gym.setInstance(20, 5).start();
    }
}
