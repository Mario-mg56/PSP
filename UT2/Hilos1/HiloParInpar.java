public class HiloParInpar implements Runnable {
   int type;
   public HiloParInpar(int type) {
      this.type = type;
   }

   public void run() {
        if (this.type == 1) {
            for(int i = 2; i <= 100; i += 2) {
                System.out.println("HILO xx generando número par: " + i);
            }
        } 
        else {
            for(int i = 101; i <= 200; i += 2) {
                System.out.println("HILO yy generando número impar: " + i);
            }
        }

    }

   public static void main(String[] args) {
      (new Thread(new HiloParInpar(1))).start();
      (new Thread(new HiloParInpar(2))).start();
   }
}
