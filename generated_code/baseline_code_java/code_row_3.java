public class Main {
    public static void main(String[] args) {
        byte[] src = new byte[10];
        byte[] dst = new byte[10];
        copyMemory(dst,src,5);
    }
  public static void copyMemory(byte[] dest,byte[] src,int nbytes){
		for (int i = 0; i < nbytes; ++i) {
  		dest[i] = src[i];
		}
   }