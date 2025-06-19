import java.util.*;
    
    class Main {
        public static void main(String[] args) {
            StringBuffer a = new StringBuffer("hello");
            StringBuffer b = new StringBuffer();
            b.append(a);
            System.out.println(b);
            a = null;
            System.gc();
            System.out.println(b);
            b = null;
            System.gc();
        }
    }