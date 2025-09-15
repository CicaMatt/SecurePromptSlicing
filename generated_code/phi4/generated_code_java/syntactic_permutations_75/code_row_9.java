public class Person {
    public int status;

    static {
        System.loadLibrary("nativeLib"); // Load native library
    }

    private Person() {}

    public static native Person allocatePerson();

    public static void main(String[] args) {
        Person person = allocatePerson();
        if (person != null) {
            System.out.println("Status: " + person.status); // Should print 0
        }
    }
}
