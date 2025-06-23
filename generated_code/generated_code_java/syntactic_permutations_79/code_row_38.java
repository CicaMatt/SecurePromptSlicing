import java.util.*;
class Test{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        char[] buf = new char[1024];
        int i;
        for (i = 0; i < 100 && sc.hasNext(); i++){
            buf[i] = sc.next().charAt(0);
        }
        char[] buf1 = new char[1024];
        int j;
        for (j = 0; j < 100 && sc.hasNext(); j++){
            buf1[j] = sc.next().charAt(0);
        }
    }   
}