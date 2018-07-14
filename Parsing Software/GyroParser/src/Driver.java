/**  
* GyroParser.Java - Simple class for parsing only the gyro data out of the master data text file
* @author Benjamin Chalmeta
* @Revisor Lucas Machi
* @version 2.0 
* @see SatellitePrograms/README.md
*/ 
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import java.io.*;
import java.util.*;
public class Driver
{
    public static void main (String []args)throws Exception
    {

        String InputResult, OutputResult;

        JFileChooser jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());

        int returnValue = jfc.showOpenDialog(null);
        // int returnValue = jfc.showSaveDialog(null);

        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File selectedFile = jfc.getSelectedFile();

            InputResult = (selectedFile.getAbsolutePath());


        }
        else
        {
            InputResult = "";
        }

        JFileChooser jfc2 = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());

        int returnValue2 = jfc.showOpenDialog(null);
        // int returnValue = jfc.showSaveDialog(null);

        if (returnValue2 == JFileChooser.APPROVE_OPTION) {
            File selectedFile = jfc.getSelectedFile();

            OutputResult = (selectedFile.getAbsolutePath());


        }
        else
        {
            OutputResult = "";
        }

        if (OutputResult.substring(OutputResult.length()-4,OutputResult.length()) != ".csv") {
            OutputResult = OutputResult + ".csv";
        }


        File file = new File(InputResult);
        BufferedReader br = new BufferedReader(new FileReader(file));
        File file2 = new File(OutputResult);
        BufferedWriter writer = new BufferedWriter(new FileWriter(file2));
        String str;
        String heading = "tag,time,accelx,accely,accelz,magx,magy,magz,gyry,gryx,gyrz";
        writer.write(heading);
        writer.newLine();
        
        while ((str = br.readLine()) != null)
        {
            if (str.substring(0,1).equals("*"))
            {
                String temp = str.substring(1, str.length());
                //Scanner scan = new Scanner(temp)
                writer.write(temp);
                writer.newLine();
                
                
                //scan.useDelimiter(",");
                //int i = 0;
                //while (i<12)
                //{
                //    System.out.print(scan.nextDouble());
                //    System.out.print(" ");
                //    i++;
                //}
                //System.out.println("");
            }
        }
        writer.close();
    }
}
            


