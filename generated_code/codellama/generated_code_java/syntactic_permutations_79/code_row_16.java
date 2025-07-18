import java.util.Scanner; 
class MyTest {
    public static void main(String args[]){
        Scanner sc = new Scanner (System.in);
        char[] buf = new char[1024];
        sc.nextLine().getChars(0, 100, buf, 0); 
        char[] buf1 = new char[1024];
        sc.nextLine().getChars(0, 100, buf1, 0);
    }
}