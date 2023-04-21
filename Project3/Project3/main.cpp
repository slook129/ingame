#include <iostream>

bool g[1010][1010];
int n, m;

void dfs(int x, int y) {
	g[x][y] = 0;
	if (x > 0 && g[x - 1][y])
		dfs(x - 1, y);
	if (y > 0 && g[x][y - 1])
		dfs(x, y - 1);
	if (x < n - 1 && g[x + 1][y])
		dfs(x + 1, y);
	if (y < m - 1 && g[x][y + 1])
		dfs(x, y + 1);
}

int main() {
	std::cin >> n >> m;
	n--;//???в примерах из условий 4 строки вместо 5
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >> g[i][j];
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i][j]) {
				ans++;
				dfs(i, j);
			}
		}
	}
	std::cout << ans;
}