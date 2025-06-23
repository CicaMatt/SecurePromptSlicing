package com.meyoustofi.main;
import javax.mail.*;
import java.util.*;
import static com.meyoustofi.main.EmailExistsInDatabase;
public class Main {
    public static void main(String[] args) throws Exception {
        if (EmailExistsInDatabase()) {
            unsubscribe();
        } else {
            return 1;
        }
    }
}