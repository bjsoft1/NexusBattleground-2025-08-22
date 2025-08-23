Content/NexusBattleground/
│
├── Animations/                            # Shared/global animation assets
│   ├── Sequences/                         # Common animation Sequences
│   ├── Montages/                          # Common animation Montages
│   └── BlendSpaces/                       # Common blendspaces & states
│
├── Data/                                  # Data-driven assets
│   ├── Enums/                             # Enum assets (Editor exposed)
│   ├── Structs/                           # Struct assets (Editor exposed)
│   └── DataTables/                        # Datatables for configs (weapons, pickups, etc.)
│
├── StaticMesh/                            # Static Mesh grouped by asset name
│   ├── Weapon_01/                         # Example weapon asset folder
│   │   ├── Meshes/                        # Mesh files for Weapon_01
│   │   ├── Textures/                      # Textures for Weapon_01
│   │   ├── Materials/                     # Materials for Weapon_01
│   │   └── Animations/                    # (Optional) Animations if used
│   ├── Prop_Crate/                        # Example prop asset folder
│   │   ├── Meshes/
│   │   ├── Textures/
│   │   └── Materials/
│   └── Environment_Tree/                  # Another example
│       ├── Meshes/
│       ├── Textures/
│       └── Materials/
│
├── SkeletalMesh/                          # Skeletal Mesh grouped by asset name
│   ├── Character_Soldier/                 # Example character asset folder
│   │   ├── Meshes/                        # Skeletal mesh for soldier
│   │   ├── Textures/                      # Textures for soldier
│   │   ├── Materials/                     # Materials for soldier
│   │   ├── Skeletons/                     # Skeleton/rig files
│   │   └── Animations/                    # Character-specific anims
│   ├── Weapon_AR/                         # Example skeletal weapon (AR)
│   │   ├── Meshes/
│   │   ├── Textures/
│   │   ├── Materials/
│   │   ├── Skeletons/
│   │   └── Animations/
│   └── Character_Zombie/                  # Another example
│       ├── Meshes/
│       ├── Textures/
│       ├── Materials/
│       ├── Skeletons/
│       └── Animations/
│
├── Blueprints/                            # Blueprint logic & prototypes
│   ├── Characters/                        # Character Blueprints
│   ├── Controllers/                       # Player/AI controller Blueprints
│   ├── GameModes/                         # GameMode Blueprints
│   ├── HUD/                               # UI/HUD Blueprints
│   ├── Items/                             # Items/Pickups Blueprints
│   └── Weapons/                           # Weapon Blueprints
│
│── UI/                                    # UI-related assets
│    ├── Widgets/                          # UMG widget Blueprints
│    ├── Textures/                         # UI textures/icons
│    └── Materials/                        # UI-specific materials
│
├── Maps/                                 # Game Maps
│   ├── M01_Training/                      # Training
│   ├── Controllers/                      # Player/AI controller Blueprints
│   ├── GameModes/                        # GameMode Blueprints
│   ├── HUD/                              # UI/HUD Blueprints
│   ├── Items/                            # Items/Pickups Blueprints
│   └── Weapons/                          # Weapon Blueprints