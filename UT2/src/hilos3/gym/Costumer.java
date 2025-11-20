package hilos3.gym;

public class Costumer extends Thread{
    int id;
    public Costumer(int id) {this.id = id;}

    @Override
    public void run() {
        try {Gym.getInstance().access(this);}
        catch (InterruptedException ex) {ex.printStackTrace();}
    }

    public void train() throws InterruptedException {
        System.out.println(id + " empieza a entrenar");
        Thread.sleep(3000);
        System.out.println(id + " termina de entrenar");
    }

    @Override
    public String toString() {return id + "";}
}
