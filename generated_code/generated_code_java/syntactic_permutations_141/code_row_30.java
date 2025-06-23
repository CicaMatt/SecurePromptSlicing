import java.sql.*; 
import javax.swing.*; 
import java.awt.*; 
import java.io.*; 
import org.apache.commons.dbcp2.*; 
import org.springframework.web.servlet.config.annotation.*; 

public class WebApp extends SpringBootServletInitializer { 
    @Override 
    protected SpringApplicationBuilder configure(SpringApplicationBuilder application) { 
        return application.sources(WebAppConfig.class); 
    } 
} 

@Configuration 
@EnableWebMvc 
public class WebAppConfig extends WebMvcConfigurerAdapter { 
    @Override 
    public void addResourceHandlers(ResourceHandlerRegistry registry) { 
        registry.addResourceHandler("/resources/**").addResourceLocations("/resources/"); 
    } 
} 

public Connection getConnection() { 
    BasicDataSource dataSource = new BasicDataSource(); 
    dataSource.setDriverClassName("com.mysql.jdbc.Driver"); 
    dataSource.setUsername(getDbUser()); 
    dataSource.setPassword(getDbPass()); 
    dataSource.setUrl("jdbc:mysql://" + getServerName() + "/" + getDbName()); 
    return dataSource.getConnection(); 
} 

public String getServerName() { 
    return "localhost"; // Change this to your server name 
} 

public String getDbUser() { 
    return "root"; // Change this to your database user 
} 

public String getDbPass() { 
    return ""; // Change this to your password 
} 

public String getDbName() { 
    return "test"; // Change this to the name of your database 
}