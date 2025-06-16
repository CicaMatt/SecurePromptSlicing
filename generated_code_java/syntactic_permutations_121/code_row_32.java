import java.io.*;
class Memory
{
  public static void main(String[] args) throws Exception
  {
    int i,j;
    File f1 = new File("f1.txt");
    FileOutputStream ostrm = new FileOutputStream(f1);
    for(i=0;i<5;i++)
      ostrm.write(i);
    ostrm.close();
    File f2 = new File("f2.txt");
    FileInputStream istrm = new FileInputStream(f1);
    FileOutputStream ostrm1 = new FileOutputStream(f2);
    int c;
    while((c=istrm.read())!=-1)
      {ostrm1.write(c);}
    istrm.close();
    ostrm1.close();
    //print the contents of second chunk
    FileInputStream istrm1 = new FileInputStream(f2);
    int d;
    while((d=istrm1.read())!=-1)
      System.out.println(d);
    istrm1.close();
  }
}