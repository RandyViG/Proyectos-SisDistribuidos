import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;  //Para manejo de ByteBuffer
import java.nio.ByteOrder;

import java.awt.*;

public class Graficos extends javax.swing.JFrame {
  
    public Graficos() {
        initComponents(); //Interfaz;
    }
    public void paint( Graphics g ) {
        int previous;
        DatagramSocket sock = null;
        int port = 7200;
        boolean draw = true;
            try{
                sock = new DatagramSocket(port); 
                sock.setReuseAddress(true);
                g.setColor(Color.WHITE);
                g.drawLine(400,0,400,600);
                g.drawLine(0,300,0,800);
                for(;;){
                    int id = 0;
                    previous = 300;
                    if (draw==true){
                        g.setColor(Color.WHITE);
                    }else{
                        g.setColor(Color.BLACK);
                    }
                    for( int i=0; i < 800; i++ ){
                        byte[] buffer = new byte[65536];
                        DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
                        sock.receive(reply);
                        byte[] data = reply.getData();
                        ByteBuffer buf = ByteBuffer.wrap(data);
                        buf.order(ByteOrder.LITTLE_ENDIAN);
            			int idd = buf.getInt();
                        int x = buf.getInt();
                        int y = buf.getInt();
			            if ( idd < id )
				            i--;
			            else{
                            id++;
                            System.out.println("id: "+ idd+ " int MIN = " + x + " int MAX = " + y);
                            g.drawLine( i,previous,x,y );
                            previous = y;
                        }
                        ByteBuffer res =  ByteBuffer.allocate(20);
			            res.order(ByteOrder.LITTLE_ENDIAN);
			            res.putInt(id);
			            res.putInt(0);
			            res.putInt(0);
			            res.putInt(0);
			            res.putInt(0);
			            DatagramPacket resp = new DatagramPacket(res.array(),res.limit(),reply.getAddress(),reply.getPort() );
			            sock.send(resp);		
                    }
                    draw=!draw;
                }

            }
            catch(IOException e){
                System.err.println("IOException " + e);
            }
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
        super.setBackground(Color.BLACK);
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
