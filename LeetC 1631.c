int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int m = heightsSize;
    int n = heightsColSize[0];
    int left = 0, right = 999999, ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int q[n * m][2];
        int qleft = 0, qright = 0;
        q[qright][0] = 0, q[qright++][1] = 0;
        int seen[m * n];
        memset(seen, 0, sizeof(seen));
        seen[0] = 1;
        while (qleft < qright) {
            int x = q[qleft][0], y = q[qleft++][1];
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0];
                int ny = y + dirs[i][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !seen[nx * n + ny] && abs(heights[x][y] - heights[nx][ny]) <= mid) {
                    q[qright][0] = nx, q[qright++][1] = ny;
                    seen[nx * n + ny] = 1;
                }
            }
        }
        if (seen[m * n - 1]) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

