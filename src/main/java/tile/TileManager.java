package tile;

import java.awt.Graphics2D;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.imageio.ImageIO;

import main.LabyrinthPanel;

public class TileManager {
    
    LabyrinthPanel labPanel;
    Tile[] tile;

    int[][] gridArr;
    public int gridMaxX;
    public int gridMaxY;

    public TileManager(LabyrinthPanel labPanel){
        this.labPanel = labPanel;
        this.gridMaxX=0;
        this.gridMaxY=0;

        this.tile = new Tile[2];
        this.gridArr = new int[labPanel.gridLimitX][labPanel.gridLimitY];

        getTileImage();
        loadLabyrinth();
    }

    public void getTileImage() {
        try {
            tile[0] = new Tile();
            tile[0].image = ImageIO.read(getClass().getResourceAsStream("/tiles/white.png"));
            tile[1] = new Tile();
            tile[1].image = ImageIO.read(getClass().getResourceAsStream("/tiles/black.png"));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void loadLabyrinth(){
        try {
            InputStream tileStream;
            if(new File("labirynt/build/windows/x64/release/output/maze.txt").isFile()) {
                tileStream = new FileInputStream("labirynt/build/windows/x64/release/output/maze.txt");
            } else {
                tileStream = new FileInputStream("labirynt/build/linux/x86_64/release/output/maze.txt");
            }
            BufferedReader tileReader = new BufferedReader(new InputStreamReader(tileStream));
            int rowCounter = 0;
            String xLine;
            while ((xLine = tileReader.readLine()) != null && rowCounter < labPanel.gridLimitY) {
                int colCounter = 0;
                String[] xSquares = xLine.split("");
                for(int i = 0; i < xSquares.length && i < labPanel.gridLimitX; i++) {
                    this.gridArr[i][rowCounter] = Integer.parseInt(xSquares[i]);
                    colCounter++;
                };
                if(colCounter > this.gridMaxX){
                    gridMaxX=colCounter;
                }
                rowCounter++;
            }
            gridMaxY=rowCounter;
            tileReader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void draw(Graphics2D g2){
        for (int y = 0; y < gridMaxY; y++) {
            for (int x = 0; x < gridMaxX; x++) {
                int tilePosX = (-labPanel.viewX + x - gridMaxX/2) * labPanel.tileSize + labPanel.screenWidth/2;
                int tilePosY = (-labPanel.viewY + y - gridMaxY/2) * labPanel.tileSize + labPanel.screenHeight/2;
                if(tilePosX >= -labPanel.tileSize && tilePosX < labPanel.screenWidth+labPanel.tileSize && tilePosY >= -labPanel.tileSize && tilePosY < labPanel.screenHeight+labPanel.tileSize){
                    g2.drawImage(tile[gridArr[x][y]].image, tilePosX, tilePosY, labPanel.tileSize, labPanel.tileSize, null);
                }
            };
        };
    }
}