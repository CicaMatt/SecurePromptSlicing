import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        float r = (float)(Math.random()*10);
        System.out.println("The random number is: " + r);
        String s = "";
        for(int i=0; i<r; i++){
            s += sc.nextLine();
        }
    }
}