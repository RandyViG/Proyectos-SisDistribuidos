import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;  //Para manejo de ByteBuffer
import java.nio.ByteOrder;

import java.awt.*;

public class Graficos extends javax.swing.JFrame {
    int x0,xN,y0,yN;  //posiciones a dibujar
    double xmin,xmax,ymin,ymax;  //valores limite de la onda
    int apAncho,apAlto;  //Valores para calcular la altura y ancho de la onda
  
    public Graficos() {
        initComponents(); //Interfaz;
        init2();  //Variables
    }

    public void init2() {
        Dimension d = size();
        apAncho = 800;
        apAlto = 600;

        x0 = y0 = 0;
        xN = apAncho-1;
        yN = apAlto-1;
        xmin = -10.0;
        xmax = 10.0;
        ymin = -1.0;
        ymax = 1.0;
    }

    // Pinta la línea entre los puntos que se toman en cada
    // segmento de cálculo de la función
    // el método paint se llama automaticamente al instanciar la clase.
    public void paint( Graphics g ) {
        double x1,y1,x2,y2;
        int j1,j2;
        DatagramSocket sock = null;
        int port = 7200;
        boolean band=true;
            try{
                sock = new DatagramSocket(port); 
                sock.setReuseAddress(true);
                for(;;){
                    j1 = ValorY( 0 );
                    if (band==true){
                        g.setColor(Color.BLACK);
                    }else{
                        g.setColor(Color.WHITE);
                    }
                    for( int i=0; i < apAncho; i++ ){
                        InetAddress host = InetAddress.getByName("localhost");
                    //final ByteBuffer buff = ByteBuffer.allocate(16);

                        byte[] buffer = new byte[65536];
                        DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
                        sock.receive(reply);
                        byte[] data = reply.getData();
                        ByteBuffer buf = ByteBuffer.wrap(data);
                        buf.order(ByteOrder.LITTLE_ENDIAN);
                        int entero1 = buf.getInt();
                        int entero2 = buf.getInt();
                        System.out.println("int MIN = " + entero1 + " int MAX = " + entero2);
                        //j2 = ValorY( entero2 );
                        g.drawLine( i,j1,entero1,entero2 );
                        j1 = entero2;
                    }
                    band=!band;
                    }

            }
            catch(IOException e){
                System.err.println("IOException " + e);
            }
        

        
    }

    private int ValorY( double valor ) {
        double conver = ((300 * (valor + 1.4)) / 2.8) - 150 ;
    double coor = 150 - conver;
    return (int)coor;
    }


  
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">                          
    private void initComponents() {

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 800, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 600, Short.MAX_VALUE)
        );
        super.setBackground(Color.WHITE);
        pack();
    }// </editor-fold>                        

    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Graficos().setVisible(true);
            }
        });
    }
}