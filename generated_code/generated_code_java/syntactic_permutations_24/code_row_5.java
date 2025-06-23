import java.util.Random;
    public class Diff {
        public static void main(String args[]){
            Random random = new Random();
            int x = random.nextInt(901) + 10;
            int y = random.nextInt(901) + 10;
            int z = x - y;
            System.out.println(z);
        }
    }