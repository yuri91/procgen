
const combos = [
	["ArrowLeft", "ArrowDown"],
	["ArrowLeft",],
	["ArrowLeft", "ArrowUp"],
	["ArrowDown",],
	[],
	["ArrowUp",],
	["ArrowRight", "ArrowDown"],
	["ArrowRight",],
	["ArrowRight", "ArrowUp"],
	["KeyD",],
	["KeyA",],
	["KeyW",],
	["KeyS",],
	["KeyQ",],
	["KeyE",],
];

let keyState = new Set();
function resetKeys()
{
	keyState.clear();
}
function listenForKeys()
{
	document.body.addEventListener("keydown", (e) => {
		keyState.add(e.code);
	});
}
function getAction()
{
	let longest = -1;
	let action = -1;
	let i = 0;
	for (const combo of combos)
	{
		let hit = true;
		for (const k of combo)
		{
			if (!keyState.has(k))
			{
				hit = false;
				break;
			}
		}
		if (hit && longest < combo.length)
		{
			longest = combo.length;
			action = i;
		}
		i++;
	}
	return action;
}

async function main()
{
	const div = document.getElementById("app");
	const opts = CheerpGame.defaultOpts();
	const c = await CheerpGame.init({
		env_name: "miner",
		rand_seed: 0,
		distribution_mode: 1,
		...opts
	});
	div.appendChild(c.getCanvas());
	const stats = document.createElement("div");
	div.appendChild(stats);

	listenForKeys();

	c.render();
	setInterval(() => {
		if (keyState.size == 0)
			return;
		const action = getAction();
		c.step(action);
		c.render();
		const state = c.observe();
		stats.innerText = JSON.stringify(state, null, 2);
		resetKeys();
	}, 100);
}
