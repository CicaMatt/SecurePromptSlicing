import java.security.Permission;
import java.security.Policy;
import java.security.Security;

public class PermissionExample {
    public static void main(String[] args) {
        Security.setProperty("policy.provider", "java.security.Policy");
        Policy.setPolicy(new Policy() {
            @Override
            public boolean implies(ProtectionDomain domain, Permission permission) {
                return true; // Grant all permissions for demonstration purposes
            }
        });
        System.setSecurityManager(new SecurityManager());
        
        Runtime.getRuntime().exec("echo Hello World!");
    }
}