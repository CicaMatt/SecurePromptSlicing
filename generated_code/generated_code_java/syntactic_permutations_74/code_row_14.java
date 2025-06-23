public class Person {
    public int status = 0;
}

public static native long allocator() { 
    return malloc(sizeof(person));
}

private static native void malloc(int size);