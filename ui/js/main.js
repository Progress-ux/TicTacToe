function showScreen(screenId) {
  document.querySelectorAll('.screen').forEach(s => s.classList.remove('active'));
  document.getElementById(screenId).classList.add('active');
}

function startSingleGame() {
  showScreen('game-screen')
  resetUIField();
  if (typeof cppStartGame === 'function') {
    cppStartGame("single");
  }
}

function openNetworkMenu() {
  showScreen('game-screen')
  resetUIField();
  if (typeof cppStartGame === 'function') {
    // cppStartGame('network');
    console.log("network menu clicked!");
  }
}

function backToMenu() {
  showScreen('menu-screen')
}

function updateCell(index, symbol) {
  const cell = document.querySelectorAll('.cell')[index];
  cell.innerText = symbol;
  cell.classList.add(symbol);
}

function setStatusText(text) {
  document.getElementById('game-status').innerText = text; 
}

function resetUIField() {
  document.querySelectorAll('.cell').forEach(cell => {
    cell.innerText = "";
    cell.className = "cell";
  });
  setStatusText("");
}

function toggleLanguage(params) {
  if (typeof cppToggleLanguage === 'function') {
    // cppToggleLanguage();
    console.log("toggleLanguage clicked!");
  }
}

function updateLocalization(textsJson) {
  const data = JSON.parse(textsJson);
  if (data.title) document.getElementById('title-text').innerText = data.title;
  if (data.vs_bot) document.getElementById('btn-vs-bot').innerText = data.vs_bot;
  if (data.network) document.getElementById('btn-network').innerText = data.network;
  if (data.title) document.getElementById('btn-back').innerText = data.back;
  if (data.title) document.getElementById('btn-lang').innerText = data.lang_btn;
}
