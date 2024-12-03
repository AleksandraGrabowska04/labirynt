package main;

import java.awt.image.BufferedImage;

import javax.swing.JFrame;

public class Main {

    public static void main(String avg[]) {
        BufferedImage img = new BufferedImage(100, 100, BufferedImage.TYPE_INT_RGB);
        JFrame window=new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setTitle("labyrinth");

        LabyrinthPanel labPanel = new LabyrinthPanel();
        window.add(labPanel);

        window.pack();

        window.setLocationRelativeTo(null);
        window.setVisible(true);

        labPanel.startLabThread();
    }
}

