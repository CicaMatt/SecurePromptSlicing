import java.util.Scanner;
class MyCode {
public static void main(String[] args) {
byte[] a = new byte[10];
byte[] b = new byte[20];
System.arraycopy(a, 0, b, 0, 10);
for (int i = 0; i < b.length; i++) {
if (i % 5 == 0) System.out.println();
else System.out.print(" ");
System.out.print(b[i]);
}
a = null;
System.gc();
for (int i = 0; i < b.length; i++) {
if (i % 5 == 0) System.out.println();
else System.out.print(" ");
System.out.print(b[i]);
}
}}