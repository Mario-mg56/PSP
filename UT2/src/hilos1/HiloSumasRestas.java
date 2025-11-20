package hilos1;

public class HiloSumasRestas implements Runnable {
    private static int num = 1000;
    private int numveces;
    private String op;

    public HiloSumasRestas (int numveces, String operacion){
        this.numveces = numveces;
        this.op = operacion;
    }

    public void run() {
        if (op.equals("+")) incrementar(numveces);
        if (op.equals("-")) decrementar(numveces);
        System.out.println("Hilo " + Thread.currentThread().getName() + " total: " + num);
    }

    public void incrementar (int numveces){num += numveces;}
    public void decrementar (int numveces){
        num -= numveces;
        System.out.println("decrementado " + numveces + " veces");
    }

    public static void main(String args[]) {
        HiloSumasRestas hiloSuma1 = new HiloSumasRestas(100, "+");
        HiloSumasRestas hiloResta2 = new HiloSumasRestas(100, "-");
        HiloSumasRestas hiloSuma3 = new HiloSumasRestas(1, "+");
        HiloSumasRestas hiloResta4 = new HiloSumasRestas(1, "-");
        new Thread(hiloSuma1, "hiloSuma1").start();
        new Thread(hiloResta2, "hiloResta2").start();
        new Thread(hiloSuma3, "hiloSuma3").start();
        new Thread(hiloResta4, "hiloResta4").start();
    }
}
