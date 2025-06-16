import java.util.*;
public class Sprint_function {
    public static void main(String[] args) {
        float a,b,c;
        String string, string2, string3;
        Random rnd = new Random();
        for (int i=0;i<5;i++){
            a=rnd.nextFloat()*100;
            b=rnd.nextFloat()*100;
            c=rnd.nextFloat()*100;
            string = String.format("%f",a);
            string2 = String.format("%f",b);
            string3 = String.format("%f",c);
            System.out.println(string+","+string2+","+string3);
        }
    }
}