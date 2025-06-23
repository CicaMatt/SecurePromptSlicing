import java.lang.Runtime;
class HelloWorld {
  public static void main(String[] args) {
    Runtime rt = Runtime.getRuntime();
    String s = "Hello World";
    int i = 5000;
    float f = 123.4f;
    char c = 'a';
    boolean b = true;
    byte by = (byte) 255;
    short sh = 32767;
    long lg = 987654321L;
    double d = 2.71828d;
    System.out.println(s);
    System.out.println(i);
    System.out.println(f);
    System.out.println(c);
    System.out.println(b);
    System.out.println(by);
    System.out.println(sh);
    System.out.println(lg);
    System.out.println(d);
  }
}