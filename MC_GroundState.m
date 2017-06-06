mc = monteCarlo(4,2000)
ferro = createFerromagneticExchange(4);
calculateEnergy(ferro, mc)

function spin = normSpin()
    spin = rand(1,3);
    spin = spin/norm(spin);
end

function config = normConfig(Nsites)
    config = zeros(Nsites, 3);
    for i = 1:Nsites
        config(i,:) = normSpin();
    end
end

function ferro = createFerromagneticExchange(Nsites)
    ferro = -ones(Nsites, Nsites);
end

function index = chooseRandomIndex(Nsites)
    index = randi(Nsites);
end

function spinr = chooseOldSpin(config, index)
    spinr = config(index,:);
end

function energy = calculateEnergy(jij, config)
    energy = 0;
    for i = 1:length(jij)
        for j = 1:length(jij)
            energy = energy + jij(i, j) * dot(config(i, :), config(j, :));
        end
    end
end

function delenergy = energyChange(jij, config, new, old, index)
    delenergy = 0;
    for i = 1: (index - 1)
        delenergy = delenergy + 2 * jij(index, i) * dot(new - old, config(i, :));
    end
    for i = (index + 1):length(jij)
        delenergy = delenergy + 2 * jij(index, i) * dot(new - old, config(i, :));
    end
end

function spins = decideSpinFlip(en, spins, index, new)
    if en < 0
        spins(index, :) = new;
    end
end

function mc = monteCarlo(Nsites, Nitr)
    mc = normConfig(Nsites);
    ferro = createFerromagneticExchange(Nsites);
    for i=1:Nitr
        ind = chooseRandomIndex(Nsites);
        oldspin = chooseOldSpin(mc, ind);
        newspin = normSpin();
        denergy = energyChange(ferro, mc, newspin, oldspin, ind);
        mc = decideSpinFlip(denergy, mc, ind, newspin);
    end
end
        
    