package edu.bloomu.homework1;

import java.util.Arrays;

/**
 * Creates the back-end for the frogs and toads game
 *
 * @author Sam Kapp
 */
public class FrogsAndToads2D {
    private static final int ROWS = 5;
    private static final int COLS = 5;
    private static final int EMPTY_SPACE = 13;

    private final String[][] grid;

    private final String ansiBoldRed = "\u001B[1;31m";
    private final String ansiBoldYellow = "\u001B[1;33m";
    private final String ansiReset = "\u001B[0m";
    private final String frog = ansiBoldRed + "F" + ansiReset;
    private final String toad = ansiBoldYellow + "T" + ansiReset;

    /**
     * Initials Frogs and Toads to the default configuration
     */
    public FrogsAndToads2D(){

        grid = new String[ROWS][COLS];
        int tile = 1;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (i < 2) grid[i][j] = frog;
                if (i == 2 && j <= 2) grid[i][j] = frog;
                if (i == 2 && j >= 2) grid[i][j] = toad;
                if (i >= 3) grid[i][j] = toad;
                if (tile == EMPTY_SPACE) grid[i][j] = "-";
                tile++;
            }
        }
    }

    /**
     * Returns the current state of the game as a string.
     */
    @Override
    public String toString(){
        String state = "   0  1  2  3  4" + '\n';
        int i = 0;
        for (String[] row : grid) {
            state += i  + " ";
            i++;
            for (String tile : row) {
                if(tile.equals("-")) state += " - ";
                else state += String.format(" %s ", tile);
            }
            state += '\n';
        }
        return state;
    }

    /**
     * Returns true if there are available moves.
     */
    public boolean canMove() {
        if (grid[0][0].equals("-")) return false;
        return !grid[4][4].equals("-");
    }

    /**
     * Takes the users input and moves the tile of their choice.
     */
    public void move(int r, int c) {
        int dashRow = 0;
        int dashCol = 0;


        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (grid[i][j].equals("-")) {
                    dashRow = i;
                    dashCol = j;
                }
            }
        }

        int rowDiff = r - dashRow;
        int colDiff = c - dashCol;

        if (grid[r][c].equals(frog)){
            if (rowDiff == 0 && colDiff == -1 || colDiff == 0 && rowDiff == -1) {
                grid[r][c] = "-";
                grid[dashRow][dashCol] = frog;
            }

            if ((rowDiff == 0 && colDiff == -2 && grid[r][c+1].equals(toad)) ||
                    (colDiff == 0 && rowDiff == -2 && grid[r+1][c].equals(toad))){
                grid[r][c] = "-";
                grid[dashRow][dashCol] = frog;
            }
        }


        if (grid[r][c].equals(toad)){
            if (rowDiff == 0 && colDiff == 1 || colDiff == 0 && rowDiff == 1) {
                grid[r][c] = "-";
                grid[dashRow][dashCol] = toad;
            }

            if ((rowDiff == 0 && colDiff == 2 && grid[r][c-1].equals(frog)) ||
                    (colDiff == 0 && rowDiff == 2 && grid[r-1][c].equals(frog))){
                grid[r][c] = "-";
                grid[dashRow][dashCol] = toad;
            }
        }
    }

    /**
     * Creates a completed grid and compares that to the users grid.
     *
     * @return true if the board is in a winning configuration.
     */
    public boolean inWinningConfig() {

        String[][] wGrid = new String[ROWS][COLS];
        int tile = 1;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (i < 2) wGrid[i][j] = toad;
                if (i == 2 && j <= 2) wGrid[i][j] = toad;
                if (i == 2 && j >= 2) wGrid[i][j] = frog;
                if (i >= 3) wGrid[i][j] = frog;
                if (tile == EMPTY_SPACE) wGrid[i][j] = "-";
                tile++;
            }
        }
        return Arrays.deepEquals(grid, wGrid);
    }
}
