import java.lang.*;
class Random{
    public static void main(String args[]){
        int x = (int)(Math.random()*900+10);
        int y = (int)(Math.random()*900+10);
        System.out.println("Difference between two numbers are:" + x - y);
    }
}